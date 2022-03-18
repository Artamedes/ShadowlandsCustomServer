#include "Player.h"
#include "ScriptMgr.h"

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

            // pvp badges
            p_Player->StoreNewItemInBestSlots(175921, 1);
            p_Player->StoreNewItemInBestSlots(178386, 1);

            switch (p_Player->GetClass())
            {
                case CLASS_WARRIOR:
                {
                    p_Player->SetPrimarySpecialization(TALENT_SPEC_WARRIOR_FURY);
                    p_Player->SetActiveTalentGroup(1);
                    static uint32 items[] = { 182997, 182994, 183032, 182999, 183018, 182984, 183015, 183002, 183027, 183039, 183036, 183037, 179543, 179543 };

                    for (uint32 item : items)
                        p_Player->StoreNewItemInBestSlots(item, 1);
                    break;
                }
                case CLASS_PALADIN:
                {
                    p_Player->SetPrimarySpecialization(TALENT_SPEC_PALADIN_RETRIBUTION);
                    p_Player->SetActiveTalentGroup(2);
                    static uint32 items[] = { 182997, 182994, 183032, 182999, 183018, 182984, 183015, 183002, 183027, 183039, 183036, 183037, 179543 };

                    for (uint32 item : items)
                        p_Player->StoreNewItemInBestSlots(item, 1);

                    break;
                }
                case CLASS_HUNTER:
                {
                    p_Player->SetPrimarySpecialization(TalentSpecialization::TALENT_SPEC_HUNTER_MARKSMAN);
                    p_Player->SetActiveTalentGroup(1);
                    static uint32 items[] = { 183001, 183003, 183033, 182988, 182977, 183014, 182976, 183012, 183006, 183039, 183037, 183036, 180081 };

                    for (uint32 item : items)
                        p_Player->StoreNewItemInBestSlots(item, 1);

                    break;
                }
                case CLASS_ROGUE:
                {

                    p_Player->SetPrimarySpecialization(TalentSpecialization::TALENT_SPEC_ROGUE_COMBAT);
                    p_Player->SetActiveTalentGroup(1);
                    static uint32 items[] = { 182980, 183029, 183034, 183009, 183019, 183007, 183005, 182993, 183030, 183040, 183037, 183036, 182408, 182408 };

                    for (uint32 item : items)
                        p_Player->StoreNewItemInBestSlots(item, 1);
                    break;
                }
                case CLASS_PRIEST:
                {
                    p_Player->SetPrimarySpecialization(TalentSpecialization::TALENT_SPEC_PRIEST_SHADOW);
                    p_Player->SetActiveTalentGroup(2);

                    static uint32 items[] = { 183021, 183020, 184778, 182998, 182996, 183022, 183004, 183011, 182979, 183037, 183036, 183040, 182405 };

                    for (uint32 item : items)
                        p_Player->StoreNewItemInBestSlots(item, 1);
                    break;
                }
                case CLASS_DEATH_KNIGHT:
                {
                    p_Player->SetPrimarySpecialization(TalentSpecialization::TALENT_SPEC_DEATHKNIGHT_FROST);
                    p_Player->SetActiveTalentGroup(1);
                    static uint32 items[] = { 182997, 182994, 183032, 182999, 183018, 182984, 183015, 183002, 183027, 183039, 183036, 183037, 179543 };

                    for (uint32 item : items)
                        p_Player->StoreNewItemInBestSlots(item, 1);
                    break;
                }
                case CLASS_SHAMAN:
                {

                    p_Player->SetPrimarySpecialization(TalentSpecialization::TALENT_SPEC_SHAMAN_ENHANCEMENT);
                    p_Player->SetActiveTalentGroup(1);
                    static uint32 items[] = { 183001, 183003, 183033, 182988, 182977, 183014, 182976, 183012, 183006, 183039, 183037, 183036, 183448, 183448 };

                    for (uint32 item : items)
                        p_Player->StoreNewItemInBestSlots(item, 1);
                    break;
                }
                case CLASS_MAGE:
                {
                    p_Player->SetPrimarySpecialization(TalentSpecialization::TALENT_SPEC_MAGE_FROST);
                    p_Player->SetActiveTalentGroup(2);

                    static uint32 items[] = { 183021, 183020, 184778, 182998, 182996, 183022, 183004, 183011, 182979, 183037, 183036, 183040, 182405 };

                    for (uint32 item : items)
                        p_Player->StoreNewItemInBestSlots(item, 1);
                    break;
                }
                case CLASS_WARLOCK:
                {
                    p_Player->SetPrimarySpecialization(TalentSpecialization::TALENT_SPEC_WARLOCK_AFFLICTION);
                    p_Player->SetActiveTalentGroup(0);

                    static uint32 items[] = { 183021, 183020, 184778, 182998, 182996, 183022, 183004, 183011, 182979, 183037, 183036, 183040, 182405 };

                    for (uint32 item : items)
                        p_Player->StoreNewItemInBestSlots(item, 1);
                    break;
                }
                case CLASS_MONK:
                {
                    p_Player->SetPrimarySpecialization(TalentSpecialization::TALENT_SPEC_MONK_BATTLEDANCER);
                    p_Player->SetActiveTalentGroup(2);
                    static uint32 items[] = { 182980, 183029, 183034, 183009, 183019, 183007, 183005, 182993, 183030, 183040, 183037, 183036, 182408, 182408 };

                    for (uint32 item : items)
                        p_Player->StoreNewItemInBestSlots(item, 1);
                    break;
                }
                case CLASS_DRUID:
                {
                    p_Player->SetPrimarySpecialization(TalentSpecialization::TALENT_SPEC_DRUID_CAT);
                    p_Player->SetActiveTalentGroup(1);
                    static uint32 items[] = { 182980, 183029, 183034, 183009, 183019, 183007, 183005, 182993, 183030, 183040, 183037, 183036, 179526 };

                    for (uint32 item : items)
                        p_Player->StoreNewItemInBestSlots(item, 1);
                    break;
                }
                case CLASS_DEMON_HUNTER:
                {
                    p_Player->SetPrimarySpecialization(TalentSpecialization::TALENT_SPEC_DEMON_HUNTER_HAVOC);
                    p_Player->SetActiveTalentGroup(0);
                    static uint32 items[] = { 182980, 183029, 183034, 183009, 183019, 183007, 183005, 182993, 183030, 183040, 183037, 183036, 182408, 182408 };

                    for (uint32 item : items)
                        p_Player->StoreNewItemInBestSlots(item, 1);
                    break;
                }
            }
        }

        void OnLogin(Player* p_Player, bool p_First) override
        {
            if (p_First)
            {
                // Learn Riding
                p_Player->CastSpell(p_Player, 33389, true);
                p_Player->CastSpell(p_Player, 33392, true);
                p_Player->CastSpell(p_Player, 34092, true);
                p_Player->CastSpell(p_Player, 90266, true);
                p_Player->LearnSpell(332400, false); // Sinful Gladiator Mount
            }
        }
};

void AddSC_LoginScript()
{
    new LoginScript();
}
