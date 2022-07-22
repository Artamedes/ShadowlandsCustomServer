#include "spell_warlock.h"

using namespace Warlock;

/// ID: 339673 Carnivorous Stalkers
class spell_carnivorous_stalkers : public AuraScript
{
    PrepareAuraScript(spell_carnivorous_stalkers);

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
        {
            caster->CastSpell(caster, Dreadbite, true);
        }
    }

    void HandleCalcProcChance(ProcEventInfo& eventInfo, float& chance)
    {
        chance = 0.0f;

        if (GetEffect(EFFECT_0) && GetEffect(EFFECT_0)->ConduitRankEntry)
            chance = GetEffect(EFFECT_0)->ConduitRankEntry->AuraPointsOverride;
    }

    void Register() override
    {
        OnProc += AuraProcFn(spell_carnivorous_stalkers::HandleProc);
        OnCalcProcChance += AuraCalcProcChanceFn(spell_carnivorous_stalkers::HandleCalcProcChance);
    }
};

struct npc_warlock_pet_felguard : public PetAI
{
    npc_warlock_pet_felguard(Creature* pCreature) : PetAI(pCreature) { }

    void IsSummonedBy(WorldObject* summoner) override
    {
        Player* player = summoner ? summoner->ToPlayer() : nullptr;
        if (!player)
            return;

        // Fel Commando
        if (auto eff = player->GetAuraEffect(339845, EFFECT_0))
        {
            if (eff->ConduitRankEntry)
            {
                me->CastSpell(me, 339848, CastSpellExtraArgs(true).AddSpellBP0(eff->ConduitRankEntry->AuraPointsOverride).AddSpellBP1(eff->ConduitRankEntry->AuraPointsOverride));
            }
        }
    }
};

void AddSC_spell_warlock_demonology()
{
    RegisterSpellScript(spell_carnivorous_stalkers);
    RegisterCreatureAI(npc_warlock_pet_felguard);
}
