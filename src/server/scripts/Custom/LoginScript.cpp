#include "Player.h"
#include "ScriptMgr.h"
#include "CovenantMgr.h"
#include "Item.h"
#include "GameTime.h"
#include "TemporarySummon.h"

class LoginScript : public PlayerScript
{
    public:
        LoginScript() : PlayerScript("LoginScript") { }

        void OnCreate(Player* p_Player) override
        {
            p_Player->StoreNewItemInBestSlots(184479, 1);
            p_Player->StoreNewItemInBestSlots(184479, 1);
            p_Player->StoreNewItemInBestSlots(184479, 1);
            p_Player->StoreNewItemInBestSlots(184479, 1);
            p_Player->StoreNewItemInBestSlots(6948, 1);

            p_Player->LearnSpell(674, true);

            // pvp badges
            p_Player->StoreNewItemInBestSlots(175921, 1, ItemContext::Raid_Raid_Finder, { 7186, 41, 30000 }); ///< Added leech to them.
            p_Player->StoreNewItemInBestSlots(178386, 1, ItemContext::Raid_Raid_Finder, { 7186, 41, 30000 }); ///< Added leech to them.

            switch (p_Player->GetClass())
            {
                case CLASS_WARRIOR:
                {
                    p_Player->SetPrimarySpecialization(TALENT_SPEC_WARRIOR_FURY);
                    p_Player->SetActiveTalentGroup(1);
                    static uint32 items[] = { 182997, 182994, 183032, 182999, 183018, 182984, 183015, 183002, 183027, 183039, 183036, 183037, 179543, 179543, 174311, 184547 };
                    static uint32 talents[] = { 22633, 19676, 22379, 22627, 19140, 22400, 22405 };

                    for (auto talent : talents)
                        p_Player->LearnTalent(talent, nullptr);

                    p_Player->SetCanTitanGrip(true);
                    for (uint32 item : items)
                        p_Player->StoreNewItemInBestSlots(item, 1, ItemContext::Raid_Raid_Finder, {7186, 30000 });
                    break;
                }
                case CLASS_PALADIN:
                {
                    p_Player->SetPrimarySpecialization(TALENT_SPEC_PALADIN_RETRIBUTION);
                    p_Player->SetActiveTalentGroup(2);
                    static uint32 items[] = { 182997, 182994, 183032, 182999, 183018, 182984, 183015, 183002, 183027, 183039, 183036, 183037, 179543, 174311, 184547 };
                    static uint32 talents[] = { 22590, 23466, 21811, 22434, 17597, 23167, 22634 };

                    for (auto talent : talents)
                        p_Player->LearnTalent(talent, nullptr);

                    for (uint32 item : items)
                        p_Player->StoreNewItemInBestSlots(item, 1, ItemContext::Raid_Raid_Finder, {7186, 30000 });

                    break;
                }
                case CLASS_HUNTER:
                {
                    p_Player->SetPrimarySpecialization(TalentSpecialization::TALENT_SPEC_HUNTER_MARKSMAN);
                    p_Player->SetActiveTalentGroup(1);
                    static uint32 items[] = { 183001, 183003, 183033, 182988, 182977, 183014, 182976, 183012, 183006, 183039, 183037, 183036, 180081, 179526 };
                    static uint32 talents[] = { 22279, 22497, 19347, 22286, 22276, 22287, 22308 };

                    for (auto talent : talents)
                        p_Player->LearnTalent(talent, nullptr);

                    for (uint32 item : items)
                        p_Player->StoreNewItemInBestSlots(item, 1, ItemContext::Raid_Raid_Finder, {7186, 30000 });

                    break;
                }
                case CLASS_ROGUE:
                {
                    p_Player->SetPrimarySpecialization(TalentSpecialization::TALENT_SPEC_ROGUE_ASSASSINATION);
                    p_Player->SetActiveTalentGroup(0);
                    static uint32 items[] = { 182980, 183029, 183034, 183009, 183019, 183007, 183005, 182993, 183030, 183040, 183037, 183036, 177861, 177861, 182408, 182408, };
                    static uint32 talents[] = { 22337, 23022, 19239, 22340, 19245, 22343, 23174 };

                    for (auto talent : talents)
                        p_Player->LearnTalent(talent, nullptr);

                    for (uint32 item : items)
                        p_Player->StoreNewItemInBestSlots(item, 1, ItemContext::Raid_Raid_Finder, {7186, 30000 });
                    break;
                }
                case CLASS_PRIEST:
                {
                    p_Player->SetPrimarySpecialization(TalentSpecialization::TALENT_SPEC_PRIEST_SHADOW);
                    p_Player->SetActiveTalentGroup(2);

                    static uint32 items[] = { 183021, 183020, 184778, 182998, 182996, 183022, 183004, 183011, 182979, 183037, 183036, 183040, 182405 };
                    static uint32 talents[] = { 22328, 22315, 23126, 21752, 22310, 21718, 21978 };

                    for (auto talent : talents)
                        p_Player->LearnTalent(talent, nullptr);

                    for (uint32 item : items)
                        p_Player->StoreNewItemInBestSlots(item, 1, ItemContext::Raid_Raid_Finder, {7186, 30000 });
                    break;
                }
                case CLASS_DEATH_KNIGHT:
                {
                    p_Player->SetPrimarySpecialization(TalentSpecialization::TALENT_SPEC_DEATHKNIGHT_FROST);
                    p_Player->SetActiveTalentGroup(1);
                    static uint32 items[] = { 182997, 182994, 183032, 182999, 183018, 182984, 183015, 183002, 183027, 183039, 183036, 183037, 184547, 184547, 179543 };
                    static uint32 talents[] = { 22016, 22019, 22515, 22523, 22527, 22531, 22537 };

                    for (auto talent : talents)
                        p_Player->LearnTalent(talent, nullptr);

                    for (uint32 item : items)
                        p_Player->StoreNewItemInBestSlots(item, 1, ItemContext::Raid_Raid_Finder, {7186, 30000 });
                    break;
                }
                case CLASS_SHAMAN:
                {

                    p_Player->SetPrimarySpecialization(TalentSpecialization::TALENT_SPEC_SHAMAN_ENHANCEMENT);
                    p_Player->SetActiveTalentGroup(1);
                    static uint32 items[] = { 183001, 183003, 183033, 182988, 182977, 183014, 182976, 183012, 183006, 183039, 183037, 183036, 183448, 183448, 174311, 182405, 182404 };
                    static uint32 talents[] = { 22355, 22636, 23165, 23089, 22144, 22351, 21972 };

                    for (auto talent : talents)
                        p_Player->LearnTalent(talent, nullptr);

                    for (uint32 item : items)
                        p_Player->StoreNewItemInBestSlots(item, 1, ItemContext::Raid_Raid_Finder, {7186, 30000 });
                    break;
                }
                case CLASS_MAGE:
                {
                    p_Player->SetPrimarySpecialization(TalentSpecialization::TALENT_SPEC_MAGE_FIRE);
                    p_Player->SetActiveTalentGroup(1);

                    static uint32 items[] = { 183021, 183020, 184778, 182998, 182996, 183022, 183004, 183011, 182979, 183037, 183036, 183040, 182405 };
                    static uint32 talents[] = { 22456, 22443, 22444, 22450, 22904, 22451, 22220 };

                    for (auto talent : talents)
                        p_Player->LearnTalent(talent, nullptr);

                    for (uint32 item : items)
                        p_Player->StoreNewItemInBestSlots(item, 1, ItemContext::Raid_Raid_Finder, {7186, 30000 });
                    break;
                }
                case CLASS_WARLOCK:
                {
                    p_Player->SetPrimarySpecialization(TalentSpecialization::TALENT_SPEC_WARLOCK_AFFLICTION);
                    p_Player->SetActiveTalentGroup(0);

                    static uint32 items[] = { 183021, 183020, 184778, 182998, 182996, 183022, 183004, 183011, 182979, 183037, 183036, 183040, 182405 };
                    static uint32 talents[] = { 23141, 22044, 19280, 19279, 23465, 23159, 19281 };

                    for (auto talent : talents)
                        p_Player->LearnTalent(talent, nullptr);

                    for (uint32 item : items)
                        p_Player->StoreNewItemInBestSlots(item, 1, ItemContext::Raid_Raid_Finder, {7186, 30000 });
                    break;
                }
                case CLASS_MONK:
                {
                    p_Player->SetPrimarySpecialization(TalentSpecialization::TALENT_SPEC_MONK_BATTLEDANCER);
                    p_Player->SetActiveTalentGroup(2);
                    static uint32 items[] = { 182980, 183029, 183034, 183009, 183019, 183007, 183005, 182993, 183030, 183040, 183037, 183036, 182408, 182408, 182405 };
                    static uint32 talents[] = { 19820, 19818, 22098, 19995, 20175, 22102, 22107 };

                    for (auto talent : talents)
                        p_Player->LearnTalent(talent, nullptr);

                    for (uint32 item : items)
                        p_Player->StoreNewItemInBestSlots(item, 1, ItemContext::Raid_Raid_Finder, {7186, 30000 });
                    break;
                }
                case CLASS_DRUID:
                {
                    p_Player->SetPrimarySpecialization(TalentSpecialization::TALENT_SPEC_DRUID_CAT);
                    p_Player->SetActiveTalentGroup(1);
                    static uint32 items[] = { 182980, 183029, 183034, 183009, 183019, 183007, 183005, 182993, 183030, 183040, 183037, 183036, 179526, 182405 };
                    static uint32 talents[] = { 22365, 18571, 22163, 18577, 21708, 22370, 21649 };

                    for (auto talent : talents)
                        p_Player->LearnTalent(talent, nullptr);

                    for (uint32 item : items)
                        p_Player->StoreNewItemInBestSlots(item, 1, ItemContext::Raid_Raid_Finder, {7186, 30000 });
                    break;
                }
                case CLASS_DEMON_HUNTER:
                {
                    p_Player->SetPrimarySpecialization(TalentSpecialization::TALENT_SPEC_DEMON_HUNTER_HAVOC);
                    p_Player->SetActiveTalentGroup(0);
                    static uint32 items[] = { 182980, 183029, 183034, 183009, 183019, 183007, 183005, 182993, 183030, 183040, 183037, 183036, 182408, 182408 };
                    static uint32 talents[] = { 21854, 22799, 22494, 21863, 21866, 21869, 21900 };

                    for (auto talent : talents)
                        p_Player->LearnTalent(talent, nullptr);

                    for (uint32 item : items)
                        p_Player->StoreNewItemInBestSlots(item, 1, ItemContext::Raid_Raid_Finder, { 7186, 30000 });
                    break;
                }
            }
        }

        // Piggy
        std::unordered_map<ObjectGuid::LowType, TimePoint> m_emoteTimer;
        void OnTextEmote(Player* player, uint32 /*textEmote*/, uint32 emoteNum, ObjectGuid /*guid*/) override
        {
            if (emoteNum == 39)
            {
                auto key = player->GetGUID().GetCounter();
                auto itr = m_emoteTimer.find(key);
                auto now = GameTime::Now();
                if (itr == m_emoteTimer.end() || now > itr->second || player->IsGameMaster())
                {
                    m_emoteTimer[key] = now + 60s;
                    if (auto summ = player->SummonCreature(700018, *player, TEMPSUMMON_TIMED_DESPAWN, 5s))
                    {
                        player->PlayDistanceSound(2837);
                        summ->SetUnitFlag(UnitFlags::UNIT_FLAG_UNINTERACTIBLE);
                        summ->SetUnitFlag(UnitFlags::UNIT_FLAG_NON_ATTACKABLE);
                        summ->GetScheduler().Schedule(2s, [](TaskContext context)
                        {
                            auto summ = context.GetUnit();
                            summ->CastSpell(summ, 356777, true); // Fade out
                        });
                    }
                }
            }
        }

        void OnLogin(Player* p_Player, bool p_First) override
        {
            p_Player->SetPlayerLocalFlag(PlayerLocalFlags::PLAYER_LOCAL_FLAG_ACCOUNT_SECURED);
            if (p_First)
            {
                if (p_Player->GetRace() == RACE_WORGEN)
                {
                    p_Player->CastSpell(p_Player, 72857, true); // Two Forms
                }
                // Learn Riding
                p_Player->CastSpell(p_Player, 33389, true);
                p_Player->CastSpell(p_Player, 33392, true);
                p_Player->CastSpell(p_Player, 34092, true);
                p_Player->CastSpell(p_Player, 90266, true);
                p_Player->LearnSpell(359372, false); // mount
                p_Player->ResurrectPlayer(1.0f);

                switch (p_Player->GetClass())
                {
                    case CLASS_WARRIOR:
                    {
                        p_Player->GetCovenantMgr()->SetCovenant(CovenantID::Kyrian);
                        p_Player->GetCovenantMgr()->SetSoulbind(SoulbindID::Pelagos);
                        break;
                    }
                    case CLASS_PALADIN:
                    {
                        p_Player->GetCovenantMgr()->SetCovenant(CovenantID::Kyrian);
                        p_Player->GetCovenantMgr()->SetSoulbind(SoulbindID::Pelagos);
                        break;
                    }
                    case CLASS_HUNTER:
                    {
                        p_Player->GetCovenantMgr()->SetCovenant(CovenantID::NightFae);
                        p_Player->GetCovenantMgr()->SetSoulbind(SoulbindID::Niya);
                        break;
                    }
                    case CLASS_ROGUE:
                    {
                        p_Player->GetCovenantMgr()->SetCovenant(CovenantID::NightFae);
                        p_Player->GetCovenantMgr()->SetSoulbind(SoulbindID::Korayn);

                        p_Player->CastSpell(p_Player, 2823, true); ///< Deadly Poison
                        p_Player->CastSpell(p_Player, 3408, true); ///< Cripple Poison
                        break;
                    }
                    case CLASS_PRIEST:
                    {
                        p_Player->GetCovenantMgr()->SetCovenant(CovenantID::Necrolord);
                        p_Player->GetCovenantMgr()->SetSoulbind(SoulbindID::PlagueDeviserMarileth);
                        break;
                    }
                    case CLASS_DEATH_KNIGHT:
                    {
                        p_Player->CastSpell(p_Player, 53431, true); // Runeforging
                        p_Player->GetCovenantMgr()->SetCovenant(CovenantID::Necrolord);
                        p_Player->GetCovenantMgr()->SetSoulbind(SoulbindID::PlagueDeviserMarileth);
                        break;
                    }
                    case CLASS_SHAMAN:
                    {
                        p_Player->GetCovenantMgr()->SetCovenant(CovenantID::Venthyr);
                        p_Player->GetCovenantMgr()->SetSoulbind(SoulbindID::NadjiaTheMistblade);
                        break;
                    }
                    case CLASS_MAGE:
                    {
                        p_Player->GetCovenantMgr()->SetCovenant(CovenantID::NightFae);
                        p_Player->GetCovenantMgr()->SetSoulbind(SoulbindID::Niya);
                        break;
                    }
                    case CLASS_WARLOCK:
                    {
                        p_Player->GetCovenantMgr()->SetCovenant(CovenantID::NightFae);
                        p_Player->GetCovenantMgr()->SetSoulbind(SoulbindID::Niya);
                        break;
                    }
                    case CLASS_MONK:
                    {
                        p_Player->GetCovenantMgr()->SetCovenant(CovenantID::Necrolord);
                        p_Player->GetCovenantMgr()->SetSoulbind(SoulbindID::PlagueDeviserMarileth);
                        break;
                    }
                    case CLASS_DRUID:
                    {
                        p_Player->GetCovenantMgr()->SetCovenant(CovenantID::NightFae);
                        p_Player->GetCovenantMgr()->SetSoulbind(SoulbindID::Niya);
                        break;
                    }
                    case CLASS_DEMON_HUNTER:
                    {
                        p_Player->GetCovenantMgr()->SetCovenant(CovenantID::NightFae);
                        p_Player->GetCovenantMgr()->SetSoulbind(SoulbindID::Niya);
                        break;
                    }
                }

                // learn all conduits
                auto covenantMgr = p_Player->GetCovenantMgr();

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
                                if (entry4->ClassID == p_Player->GetClass())
                                {
                                    auto item = Item::CreateItem(entry->ItemID, 1, ItemContext::NONE);
                                    if (item)
                                    {
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

            p_Player->RemoveAurasDueToSpell(141480); // Self stun
            p_Player->RemoveAurasDueToSpell(163091); // Self stun
        }
};

void AddSC_LoginScript()
{
    new LoginScript();
}
