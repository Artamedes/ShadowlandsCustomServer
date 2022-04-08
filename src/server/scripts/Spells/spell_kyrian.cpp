#include "SpellMgr.h"
#include "Unit.h"
#include "SpellScript.h"
#include "CovenantMgr.h"
#include "Player.h"
#include "SpellHistory.h"

struct npc_kyrian_steward : public ScriptedAI
{
    public:
        npc_kyrian_steward(Creature* creature) : ScriptedAI(creature) { }

        void InitializeAI() override
        {

        }

        void IsSummonedBy(WorldObject* o) override
        {
            if (!o)
                return;
            auto owner = o->ToUnit();
            if (!owner)
                return;

            me->SetCreatorGUID(owner->GetGUID());
            me->GetMotionMaster()->MoveFollow(owner, PET_FOLLOW_DIST, me->GetFollowAngle());
            DoCastSelf(326346); // (Steward Name Override [DNT])
            DoCastSelf(326506); // (Steward Spawn VFX [DNT])
            DoCastSelf(324749); // (Carry Tray [DNT])
            DoCastSelf(324791); // (Carry Bottle[DNT])
            DoCastSelf(344432); // (At Your Service)
        }
        // 342477- ping steward bard

        void Reset() override
        {

        }

        void UpdateAI(uint32 diff) override
        {
            if (!gavePotsToOwner && me->GetOwner() && me->GetOwner()->IsPlayer())
            {
                if (me->GetDistance2d(me->GetOwner()) <= 3.0f)
                {
                    for (int i = 0; i < 3; ++i)
                    {
                        DoCast(me->GetOwner(), 324743, true);
                        me->GetOwner()->ToPlayer()->AddItem(177278, 1);
                    }
                    me->RemoveAurasDueToSpell(324791); // Carry Bottle
                    gavePotsToOwner = true;
                }
            }
        }

        enum MenuIds
        {
            IdMain = 40275, // Hoo! Can help? Can do many tasks, or just keep company!
            IdOne = 42480, // What can I do-hoo for you? Can help with one thing, so pick careful! Will take time for me to help again -- one hour. Very busy!
            IdTwo = 42481, // Hoo-ooo! Can help with one big task, but just one. Will take time for me to help again--a few hours. Busy busy!
        };

        bool OnGossipHello(Player* player) override
        {
            if (player == me->GetOwner())
            {
                ClearGossipMenuFor(player);
                AddGossipItemFor(player, GossipOptionIcon::None, "I need a favor. (1 hr cooldown)", 0, 7);
                AddGossipItemFor(player, GossipOptionIcon::None, "I have a special request. (4 hr cooldown)", 0, 3);
                AddGossipItemFor(player, GossipOptionIcon::None, "Tell one of my friends how great they are! (1 day cooldown)", 0, 6);
                AddGossipItemFor(player, GossipOptionIcon::None, "Can you play me a song?", 0, 2);
                AddGossipItemFor(player, GossipOptionIcon::None, "Thank you. See you later!", 0, 8);

                // (26712, 3, 0, 'Let\'s talk about something else.',                           0, 1, 1, 0, 25502, 0, 0, 0, NULL, 0, 42979),
                // (25502, 8, 0, 'Can you play me a song?',                                     0, 1, 1, 0, UNKNOWN, UNKNOWN, 0, 0, NULL, 0, 42979),
                // (25502, 1, 0, 'I have a special request. (4 hr cooldown)',                   0, 1, 1, 0, 26713, 0, 0, 0, NULL, 0, 42979),
                // (26713, 0, 0, 'I\'d like to change my talents.',                             0, 1, 1, 0, UNKNOWN, UNKNOWN, 0, 0, NULL, 0, 42979),
                // (26712, 0, 1, 'Would you please take these items off my hands?',             0, 3, 128, 0, UNKNOWN, UNKNOWN, 0, 0, NULL, 0, 42979),
                // (25502, 3, 0, 'Tell one of my friends how great they are! (1 day cooldown)', 0, 1, 1, 0, UNKNOWN, UNKNOWN, 0, 0, NULL, 0, 42979),
                // (25502, 0, 0, 'I need a favor. (1 hr cooldown)',                             0, 1, 1, 0, 26712, 0, 0, 0, NULL, 0, 42979),
                // (25502, 19, 0, 'Thank you. See you later!',                                  0, 1, 1, 0, UNKNOWN, UNKNOWN, 0, 0, NULL, 0, 42979),
                SendGossipMenuFor(player, IdMain, me);
            }
            return true;
        }

        bool OnGossipSelect(Player* player, uint32 menuId, uint32 gossipId) override
        {
            uint32 actionId = player->PlayerTalkClass->GetGossipOptionAction(gossipId);
            ClearGossipMenuFor(player);

            switch (actionId)
            {
                case 1:
                    return OnGossipHello(player);
                case 7:
                    AddGossipItemFor(player, GossipOptionIcon::None, "Would you please take these items off my hands?", 0, 5);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Let\'s talk about something else.", 0, 1);
                    SendGossipMenuFor(player, IdOne, me);
                    break;
                case 3:
                    AddGossipItemFor(player, GossipOptionIcon::None, "I\'d like to change my talents.", 0, 4);
                    AddGossipItemFor(player, GossipOptionIcon::None, "Let\'s talk about something else.", 0, 1);
                    SendGossipMenuFor(player, IdTwo, me);
                    break;
                case 4:
                    CloseGossipMenuFor(player);
                    player->CastSpell(player, 325012, true);
                    break;
                case 5:
                    player->GetSession()->SendListInventory(me->GetGUID());
                    break;
                case 6: // tell my friend how great they are
                    CloseGossipMenuFor(player);
                    break;
                case 2: // play song
                    CloseGossipMenuFor(player);

                    break;
                case 8: // despawn
                    CloseGossipMenuFor(player);
                    DoCastSelf(324807); // dismiss
                    me->DespawnOrUnsummon(5s);
                    break;
            }

            return true;
        }

        bool gavePotsToOwner = false;
};

// ID - 353248 Effusive Anima Accelerator
class spell_kyrian_effusive_anima_accelerator : public SpellScript
{
    PrepareSpellScript(spell_kyrian_effusive_anima_accelerator);

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        auto caster = GetCaster();
        if (!caster)
            return;
        if (targets.empty())
            return;

        int32 targetsSize = targets.size();
        int32 cdr = 3000 * targetsSize;
        if (cdr >= 15000)
            cdr = 15000;

        switch (caster->GetClass())
        {
            case CLASS_ROGUE:
                caster->GetSpellHistory()->ModifyCooldown(323547, -cdr); // Echoing Reprimand
                break;
        }
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_kyrian_effusive_anima_accelerator::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ENEMY);
    }
};

void AddSC_spell_kyrian()
{
    RegisterCreatureAI(npc_kyrian_steward);
    RegisterSpellScript(spell_kyrian_effusive_anima_accelerator);
}
