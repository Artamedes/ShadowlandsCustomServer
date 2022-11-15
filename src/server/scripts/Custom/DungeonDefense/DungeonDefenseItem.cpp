#include "DungeonDefense.h"

class DarkmaulCitadel_DungeonDefenseSpawner_ItemScript : public ItemScript
{
public:
    DarkmaulCitadel_DungeonDefenseSpawner_ItemScript() : ItemScript("DarkmaulCitadel_DungeonDefenseSpawner_ItemScript") { }

    bool OnUse(Player* player, Item* item, SpellCastTargets const& /*targets*/, ObjectGuid /*castId*/) override
    {
        MainMenu(player, item);
        return true;
    }

    void MainMenu(Player* player, Item* item)
    {
        if (player->GetMapId() != DarkmaulMapId)
            return;

        ClearGossipMenuFor(player);

        if (auto instance = player->GetInstanceScript())
        {
            if (instance->GetBossState(BossCrystal) == IN_PROGRESS)
            {
                std::ostringstream ss;

                ss << "Rift Energy: " << player->GetCurrency(RiftEnergy) << "/" << instance->GetData(DataGetMaxEnergy);
                AddGossipItemFor(player, GossipOptionIcon::None, ss.str(), 0, 0, [this, player, item](std::string /*callback*/)
                {
                    MainMenu(player, item);
                });

                ss.clear();
                ss.str("");
                auto currDefensePoints = instance->GetData(DataGetDefensePoints);
                auto maxDefensePoints = instance->GetData(DataGetMaxDefensePoints);
                ss << "Defense Points: " << currDefensePoints << "/" << maxDefensePoints;
                AddGossipItemFor(player, GossipOptionIcon::None, ss.str(), 0, 0, [this, player, item](std::string /*callback*/)
                {
                    MainMenu(player, item);
                });

                for (auto const& itr : sDungeonDefenseMgr->m_CreatureStorage)
                {
                    if (!itr.second.RiftEnergyCost)
                        continue;

                    auto creatureTemplate = sObjectMgr->GetCreatureTemplate(itr.first.first);
                    if (!creatureTemplate)
                        continue;

                    uint32 cost = itr.second.RiftEnergyCost;
                    uint32 defensePoints = itr.second.DefensePoints;
                    ss.clear();
                    ss.str("");
                    ss << "Spawn " << creatureTemplate->Name;

                    if (player->GetCurrency(RiftEnergy) >= cost)
                        ss << " Cost: " << cost;
                    else
                        ss << " |cffFF0000Cost: " << cost;

                    if (maxDefensePoints - currDefensePoints >= defensePoints)
                        ss << "\nDefense Points: " << defensePoints;
                    else
                        ss << "\n|cffFF0000Defense Points: " << defensePoints;

                    AddGossipItemFor(player, GossipOptionIcon::None, ss.str(), 0, 0, [this, player, item, creatureTemplate, cost, defensePoints, currDefensePoints, maxDefensePoints](std::string /*callback*/)
                    {
                        if (auto instance = player->GetInstanceScript())
                        {
                            if (auto crystal = instance->GetCreature(BossCrystal))
                            {
                                if (player->GetCurrency(RiftEnergy) >= cost && maxDefensePoints - currDefensePoints >= defensePoints)
                                {
                                    player->ModifyCurrency(RiftEnergy, -static_cast<int32>(cost));
                                    instance->SetData(SetAddDefensePoints, defensePoints);
                                    ChatHandler(player).PSendSysMessage("|cffFFA600-%u Rift Energy", cost);
                                    if (auto defense = crystal->SummonCreature(creatureTemplate->Entry, *player, TEMPSUMMON_MANUAL_DESPAWN, 0))
                                    {
                                        if (defense->AI())
                                        {
                                            defense->AI()->SetData(SetRiftEnergy, cost);
                                            defense->AI()->SetData(SetDefensePoints, defensePoints);
                                        }
                                    }
                                }
                            }
                        }
                        MainMenu(player, item);
                    });
                }
            }
        }
        SendGossipMenuFor(player, DungeonDefenseItemNpcTextId, item->GetGUID());
    }
};

void AddSC_DungeonDefenseItem()
{
    new DarkmaulCitadel_DungeonDefenseSpawner_ItemScript();
}
