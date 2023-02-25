#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "WorldSession.h"

enum DreadscarRift
{
    TestDummy,

    NpcTestConduit = 802002,
};

const Position TestConduitPos = { 3452.24f, 1554.11f, 436.707f, 3.18628f };

struct npc_live_dummy : ScriptedAI
{
public:
	npc_live_dummy(Creature* creature) : ScriptedAI(creature) {}

    bool conduitUp = true;

    void DamageTaken(Unit* attacker, uint32& damage, DamageEffectType /*damageType*/, SpellInfo const* /*spellInfo = nullptr*/) override
    {
        if (damage >= me->GetHealth())
        {
            damage = 0;

            me->SetHealth(me->CountPctFromMaxHealth(50));
        }
    }

    Position const DummyStartPos = {4267.54f, -2805.66f, 5.26688f, 5.40941f};

    void EnterEvadeMode(EvadeReason why) override
    {
        conduitUp = true;
        me->GetMotionMaster()->MoveTargetedHome();
        me->SetHealth(me->CountPctFromMaxHealth(100));
    }
};

struct npc_test_conduit : public ScriptedAI
{
public:
    npc_test_conduit(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI() override
    {
        SetCombatMovement(false);
        me->SetReactState(REACT_PASSIVE);
    }

    void UpdateAI(uint32 diff) override
    {
        if (me->isDead())
            return;

        if (auto livedummy = ObjectAccessor::GetCreature(*me, CurrentDummy))
            DoCast(livedummy, 353401); // ID - 353401 Eye of the Jailer Channel

        me->SetUnitFlag(UnitFlags::UNIT_FLAG_STUNNED);
    }

    void doneTesting()
    {
        if (auto livedummy = ObjectAccessor::GetCreature(*me, CurrentDummy))
        {
            livedummy->KillSelf();
            livedummy->DespawnOrUnsummon(5s);
        }

        CurrentDummy.Clear();
    }

    void spawnDummy()
    {
        if (CurrentDummy.IsEmpty())
            if (Creature* creature = DoSummon(802003, { 4267.65f, -2805.53f, 5.27405f, 5.44632f }, 0s, TEMPSUMMON_MANUAL_DESPAWN))
                CurrentDummy = creature->GetGUID();
    }

    ObjectGuid CurrentDummy;

    bool OnGossipHello(Player* player) override
    {
        ClearGossipMenuFor(player);

        if (player->GetSession()->GetSecurity() >= SEC_GAMEMASTER)
        {
            if (!CurrentDummy.IsEmpty())
            {
                AddGossipItemFor(player, GossipOptionNpc::None, "I'm done testing.", 0, 1);
            }
            else
            {
                AddGossipItemFor(player, GossipOptionNpc::None, "Summon the bot.", 0, 2);
            }
            SendGossipMenuFor(player, 802002, me);
        }
        else
        {
            SendGossipMenuFor(player, 8020020, me);
        }

        return true;
    }

    bool OnGossipSelect(Player* player, uint32 menuid, uint32 gossipid) override
    {
        uint32 actionid = player->PlayerTalkClass->GetGossipOptionAction(gossipid);

        CloseGossipMenuFor(player);

        if (actionid == 1)
        {
            doneTesting();
        }

        if (actionid == 2)
        {
            spawnDummy();
        }

        return true;
    }
};

void AddSC_QuelTest()
{
	RegisterCreatureAI(npc_live_dummy);
    RegisterCreatureAI(npc_test_conduit);
}
