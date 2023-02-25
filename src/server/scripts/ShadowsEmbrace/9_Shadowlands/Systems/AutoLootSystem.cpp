#include "ScriptMgr.h"
#include "Player.h"
#include "Creature.h"
#include "Map.h"
#include "Group.h"
#include "DatabaseEnv.h"

enum class AutoLootTypes
{
    ItemId     = 0,
    CurrencyId = 1,
};

struct AutoLootStruct
{
    AutoLootTypes Type;
    uint32 DifficultyID;
    uint32 ID;
    uint32 MinQuantity;
    uint32 MaxQuantity;
    uint32 Flags;
    uint32 Chance;
};

enum AutoLootFlags
{
    AUTO_LOOT_FLAG_SPLIT_QUANTITY    = 0x1,
    AUTO_LOOT_FLAG_IGNORE_GROUP_DIST = 0x2,
};

class AutoLootSystem
{
    public:
        static AutoLootSystem* instance()
        {
            static AutoLootSystem l_Instance;
            return &l_Instance;
        }

        void LoadFromDB()
        {
            m_AutoLootContainer.clear();
            QueryResult l_Result = WorldDatabase.Query("SELECT LootID, DifficultyID, Type, ID, MinQuantity, MaxQuantity, Flags, Chance FROM z_creature_autoloot");
            if (!l_Result)
                return;

            do
            {
                Field* l_Fields = l_Result->Fetch();

                AutoLootStruct l_Struct;
                
                l_Struct.DifficultyID   = l_Fields[1].GetUInt32();
                l_Struct.Type       = static_cast<AutoLootTypes>(l_Fields[2].GetUInt32());
                l_Struct.ID         = l_Fields[3].GetUInt32();
                l_Struct.MinQuantity= l_Fields[4].GetUInt32();
                l_Struct.MaxQuantity= l_Fields[5].GetUInt32();
                l_Struct.Flags      = l_Fields[6].GetUInt32();
                l_Struct.Chance     = l_Fields[7].GetUInt32();

                if (l_Struct.MinQuantity > l_Struct.MaxQuantity)
                    l_Struct.MaxQuantity = l_Struct.MinQuantity;

                if (l_Struct.Chance >= 100)
                    l_Struct.Chance = 100;

                m_AutoLootContainer.insert({ l_Fields[0].GetUInt32(), l_Struct });

            } while (l_Result->NextRow());
        }

        std::unordered_multimap<uint32, AutoLootStruct> m_AutoLootContainer;

};

#define sAutoLootSystem AutoLootSystem::instance()

class AutoLootSystem_PlayerScript : public PlayerScript
{
    public:
        AutoLootSystem_PlayerScript() : PlayerScript("AutoLootSystem_PlayerScript") { }

        void RewardPlayerWith(Player* p_Player, AutoLootStruct const* p_Struct, uint32 p_RewardQuantity)
        {
            switch (p_Struct->Type)
            {
                case AutoLootTypes::CurrencyId:
                    p_Player->ModifyCurrency(p_Struct->ID, p_RewardQuantity);
                    break;
                case AutoLootTypes::ItemId:
                    if (!p_Player->AddItem(p_Struct->ID, p_RewardQuantity))
                        p_Player->SendItemRetrievalMail(p_Struct->ID, p_RewardQuantity, ItemContext::Dungeon_Normal);
                    break;
            }
        }

        void OnCreatureKill(Player* p_Player, Creature* p_Creature) override
        {
            uint32 l_LootId = p_Creature->GetCreatureTemplate()->lootid;
            if (l_LootId > 0)
            {
                auto l_Itr = sAutoLootSystem->m_AutoLootContainer.equal_range(l_LootId);
                for (auto l_I = l_Itr.first; l_I != l_Itr.second; ++l_I)
                {
                    AutoLootStruct const* l_Struct = &l_I->second;

                    bool l_DifficultyID = p_Player->GetMap()->GetDifficultyID();
                    bool l_IsAtReward = p_Player->IsAtGroupRewardDistance(p_Creature);
                    bool l_IsInGroup = p_Player->GetGroup() != nullptr;

                    if (!l_IsAtReward)
                        l_IsAtReward = l_Struct->Flags & AutoLootFlags::AUTO_LOOT_FLAG_IGNORE_GROUP_DIST;

                    if (!l_IsAtReward)
                        continue;

                    if (l_Struct->DifficultyID != 0 && l_Struct->DifficultyID != static_cast<uint32>(l_DifficultyID))
                        continue;

                    uint32 l_RewardQuantity = urand(l_Struct->MinQuantity, l_Struct->MaxQuantity);
                    uint32 l_ActualGroupSize = 0;

                    if (l_IsInGroup)
                    {
                        for (GroupReference const* ref = p_Player->GetGroup()->GetFirstMember(); ref != nullptr; ref = ref->next())
                        {
                            if (Player const* groupMember = ref->GetSource())
                            {
                                bool l_IsAtReward = groupMember->IsAtGroupRewardDistance(p_Creature);

                                if (!l_IsAtReward)
                                    l_IsAtReward = l_Struct->Flags & AutoLootFlags::AUTO_LOOT_FLAG_IGNORE_GROUP_DIST;

                                if (!l_IsAtReward)
                                    continue;

                                ++l_ActualGroupSize;
                            }
                        }

                        if (l_ActualGroupSize > 0 && l_Struct->Flags & AutoLootFlags::AUTO_LOOT_FLAG_SPLIT_QUANTITY)
                            l_RewardQuantity /= l_ActualGroupSize;

                        for (GroupReference const* ref = p_Player->GetGroup()->GetFirstMember(); ref != nullptr; ref = ref->next())
                        {
                            if (Player* groupMember = ref->GetSource())
                            {
                                bool l_IsAtReward = groupMember->IsAtGroupRewardDistance(p_Creature);

                                if (!l_IsAtReward)
                                    l_IsAtReward = l_Struct->Flags & AutoLootFlags::AUTO_LOOT_FLAG_IGNORE_GROUP_DIST;

                                if (!l_IsAtReward)
                                    continue;

                                if (roll_chance_i(l_Struct->Chance))
                                    RewardPlayerWith(groupMember, l_Struct, l_RewardQuantity);
                            }
                        }
                    }
                    else
                    {
                        if (roll_chance_i(l_Struct->Chance))
                            RewardPlayerWith(p_Player, l_Struct, l_RewardQuantity);
                    }
                }
            }
        }
};

void AddSC_AutoLootSystem()
{
    sAutoLootSystem->LoadFromDB();
    new AutoLootSystem_PlayerScript();
}
