#include "spell_dh.h"

using namespace DH;

/// ID: 338835 Ravenous Consumption
class spell_ravenous_consumption : public AuraScript
{
    PrepareAuraScript(spell_ravenous_consumption);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return false;

        return eventInfo.GetSpellInfo()->Id == ConsumeMagic;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        if (auto caster = GetCaster())
            if (auto eff = GetEffect(EFFECT_0))
                if (eff->ConduitRankEntry)
                    if (auto target = eventInfo.GetActionTarget())
                        caster->CastSpell(target, ConsumeMagic, true);
    }

    void OnCalcProc(ProcEventInfo& eventInfo, float& chance)
    {
        chance = 0.0f;
        if (auto eff = GetEffect(EFFECT_0))
            if (eff->ConduitRankEntry)
                chance = eff->ConduitRankEntry->AuraPointsOverride;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_ravenous_consumption::CheckProc);
        OnProc += AuraProcFn(spell_ravenous_consumption::HandleProc);
        OnCalcProcChance += AuraCalcProcChanceFn(spell_ravenous_consumption::OnCalcProc);
    }
};

enum eFodderToTheFlame
{
    FodderToTheFlameDmg = 350631,

    FodderToTheFlameSumm1 = 329621,
    FodderToTheFlameSumm2 = 329622,
    FodderToTheFlameSumm3 = 329625,
    FodderToTheFlameSumm4 = 329626,
    FodderToTheFlameSumm5 = 329627,
    FodderToTheFlameSumm6 = 329633,

    FodderToTheFlameDemonRemoveCOnflict = 328606,
    UnstoppableConflict   = 328605,
    DemonSpawn = 336862,

    FodderToFlameShatteredSoul = 328950,
};

/// ID: 342357 Fodder to the Flame
class spell_fodder_to_the_flame : public AuraScript
{
    PrepareAuraScript(spell_fodder_to_the_flame);

    void HandleApply(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (auto caster = GetCaster())
        {
            caster->CastSpell(caster, RAND(FodderToTheFlameSumm1, FodderToTheFlameSumm2, FodderToTheFlameSumm3, FodderToTheFlameSumm4, FodderToTheFlameSumm5, FodderToTheFlameSumm6), true);
        }
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_fodder_to_the_flame::HandleApply, EFFECT_0, SPELL_AURA_FORCE_REACTION, AURA_EFFECT_HANDLE_REAL);
    }
};

// legendary cast 207744 204021 207744
 
struct npc_condemed_demon : public ScriptedAI
{
public:
    npc_condemed_demon(Creature* creature) : ScriptedAI(creature) { }

    void IsSummonedBy(WorldObject* owner) override
    {
        me->SetUnitFlag(UNIT_FLAG_CAN_SWIM | UNIT_FLAG_RENAME);
        me->SetUnitFlag2(UNIT_FLAG2_REGENERATE_POWER | UNIT_FLAG2_DONT_FADE_IN);
        me->SetUnitFlag3(UNIT_FLAG3_UNTARGETABLE_FROM_UI | UNIT_FLAG3_SUPPRESS_NPC_SOUNDS);
            // [1] Flags: 557072 0x88010 UNIT_FLAG_IN_COMBAT UNIT_FLAG_CAN_SWIM UNIT_FLAG_RENAME
            // [1] Flags2 : 2080 0x820
            // [1] Flags3 : 557056 0x88000

        me->DespawnOrUnsummon(20s);
        me->SetReactState(REACT_PASSIVE);
        me->AddUnitState(UNIT_STATE_EVADE);
        if (me->ToTempSummon())
            if (auto owner = me->ToTempSummon()->GetSummonerUnit())
            {
                DoCast(owner, UnstoppableConflict, true);
                DoCastSelf(DemonSpawn);
                scheduler.Schedule(2s, [this](TaskContext context)
                {
                    if (me->ToTempSummon())
                        if (auto owner = me->ToTempSummon()->GetSummonerUnit())
                        {
                            me->ClearUnitState(UNIT_STATE_EVADE);
                            me->SetReactState(REACT_AGGRESSIVE);
                            AttackStart(owner);
                        }
                });
            }
    }

    void JustDied(Unit* /*killer*/)
    {
        if (me->ToTempSummon())
            if (auto owner = me->ToTempSummon()->GetSummonerUnit())
            {
                DoCast(owner, FodderToTheFlameDemonRemoveCOnflict, true);
                // fiery brand is done BEFORE!!
                owner->CastSpell(*me, FodderToTheFlameDmg, true);
                owner->CastSpell(*me, FodderToFlameShatteredSoul, true);
            }
    }

    void UpdateAI(uint32 diff) override
    {
        scheduler.Update(diff);

        if (!UpdateVictim())
        {
            if (me->ToTempSummon())
                if (auto owner = me->ToTempSummon()->GetSummonerUnit())
                {
                    AttackStart(owner);
                }
            return;
        }

        DoMeleeAttackIfReady();
    }

    TaskScheduler scheduler;
};

void AddSC_spell_dh_covenant()
{
    RegisterSpellScript(spell_ravenous_consumption);
    RegisterSpellScript(spell_fodder_to_the_flame);
    RegisterCreatureAI(npc_condemed_demon);
}
