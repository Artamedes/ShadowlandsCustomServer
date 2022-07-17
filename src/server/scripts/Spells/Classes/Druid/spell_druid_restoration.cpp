#include "spell_druid.h"

using namespace Druid;

/// ID: 364365 Renewing Bloom
class spell_renewing_bloom : public AuraScript
{
    PrepareAuraScript(spell_renewing_bloom);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == Rejuvenation;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_renewing_bloom::CheckProc);
    }
};

/// ID: 363495 Ephemeral Incarnation
class spell_ephemeral_incarnation : public AuraScript
{
    PrepareAuraScript(spell_ephemeral_incarnation);

    enum eEphmeralIncarnation
    {
        EphermeralBlossom = 363813,
    };

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == Swiftmend;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
        {
            if (auto aura = caster->GetAura(EphermeralBlossom))
            {
                if (aura->GetStackAmount() >= 2)
                {
                    uint32 currDur = 0;
                    if (auto incarn = caster->GetAura(IncarnationTreeOfLife))
                        currDur += incarn->GetDuration();

                    caster->CastSpell(caster, IncarnationTreeOfLife, CastSpellExtraArgs(true).AddSpellMod(SpellValueMod::SPELLVALUE_DURATION, 9000 + currDur));
                    aura->Remove();
                    return;
                }
            }

            caster->CastSpell(caster, EphermeralBlossom, true);
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_ephemeral_incarnation::CheckProc);
        OnProc += AuraProcFn(spell_ephemeral_incarnation::HandleProc);
    }
};

void AddSC_spell_druid_restoration()
{
    RegisterSpellScript(spell_renewing_bloom);
    RegisterSpellScript(spell_ephemeral_incarnation);
}
