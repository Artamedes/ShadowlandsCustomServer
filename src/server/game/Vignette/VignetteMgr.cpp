////////////////////////////////////////////////////////////////////////////////
//
//  NazmirStudio 2018-2020
//
////////////////////////////////////////////////////////////////////////////////

#include "AreaTrigger.h"
#include "Conversation.h"
#include "Corpse.h"
#include "Creature.h"
#include "SceneObject.h"
#include "SceneMgr.h"
#include "DB2Stores.h"
#include "DynamicObject.h"
#include "MiscPackets.h"
#include "ObjectAccessor.h"
#include "ObjectGuid.h"
#include "VignetteMgr.h"
#include <G3D/Vector3.h>

namespace Vignette
{
    Manager::Manager(Player const* player)
    {
        m_Owner = player;
    }

    Manager::~Manager()
    {
        m_Owner = nullptr;

        for (auto iterator : m_Vignettes)
            delete iterator.second;
    }

    Entity* Manager::CreateAndAddVignette(VignetteEntry const* vignetteEntry, uint32 const mapId, Vignette::Type const vignetteType, G3D::Vector3 const position, uint32 zoneID, ObjectGuid const sourceGuid /*= ObjectGuid::Empty*/)
    {
        // Check for duplicated vignettes
        for (auto vignette : m_Vignettes)
        {
            // Return if same vignette has already been created
            if (vignette.second->GetVignetteEntry()->Id == vignetteEntry->Id && vignette.second->GeSourceGuid() == sourceGuid)
                return nullptr;
        }

        Entity* vignette = new Vignette::Entity(vignetteEntry, mapId);
        vignette->Create(vignetteType, position, vignetteEntry, mapId, zoneID, sourceGuid);

        m_Vignettes.insert(std::make_pair(vignette->GetGuid(), vignette));
        m_AddedVignette.insert(vignette->GetGuid());

        return vignette;
    }

    void Manager::DestroyAndRemoveVignetteByEntry(VignetteEntry const* vignetteEntry)
    {
        if (vignetteEntry == nullptr)
            return;

        for (auto iterator = m_Vignettes.begin(); iterator != m_Vignettes.end();)
        {
            if (iterator->second->GetVignetteEntry()->Id == vignetteEntry->Id)
            {
                delete iterator->second;
                m_RemovedVignette.insert(iterator->first);
                iterator = m_Vignettes.erase(iterator);
                continue;
            }

            ++iterator;
        }
    }

    void Manager::DestroyAndRemoveVignettes(std::function<bool(Entity* const)> lamba)
    {
        for (auto iterator = m_Vignettes.begin(); iterator != m_Vignettes.end();)
        {
            if (lamba(iterator->second))
            {
                delete iterator->second;
                m_RemovedVignette.insert(iterator->first);
                iterator = m_Vignettes.erase(iterator);
                continue;
            }

            ++iterator;
        }
    }

    void Manager::SendVignetteUpdateToClient()
    {
        WorldPackets::Misc::ClientVignetteUpdate ClientVignetteUpdate;

        ClientVignetteUpdate.ForceUpdate = false;

        for (auto const& guid : m_RemovedVignette)
            ClientVignetteUpdate.RemovedIDs.emplace_back(guid);

        for (auto const& guid : m_AddedVignette)
        {
            ClientVignetteUpdate.AddedIDs.emplace_back(guid);

            auto findResult = m_Vignettes.find(guid);
            if (findResult == m_Vignettes.end())
                continue;

            auto vignette = findResult->second;

            WorldPackets::Misc::VignetteClientData data;

            data.Position = vignette->GetPosition();
            data.ObjGUID = vignette->GetGuid();
            data.VignetteID = vignette->GetVignetteEntry()->Id;
            data.ZoneID = vignette->GetZoneID();

            ClientVignetteUpdate.AddedDatas.emplace_back(data);
        }

        for (auto const& guid : m_UpdatedVignette)
        {
            ClientVignetteUpdate.UpdatedIDs.emplace_back(guid);

            auto findResult = m_Vignettes.find(guid);
            if (findResult == m_Vignettes.end())
                continue;

            auto vignette = findResult->second;

            WorldPackets::Misc::VignetteClientData data;

            data.Position = vignette->GetPosition();
            data.ObjGUID = vignette->GetGuid();
            data.VignetteID = vignette->GetVignetteEntry()->Id;
            data.ZoneID = vignette->GetZoneID();

            ClientVignetteUpdate.UpdatedDatas.emplace_back(data);
        }

        m_Owner->GetSession()->SendPacket(ClientVignetteUpdate.Write());

        m_AddedVignette.clear();
        m_RemovedVignette.clear();
        m_UpdatedVignette.clear();
    }

    void Manager::Update()
    {
        for (auto iterator : m_Vignettes)
        {
            auto vignette = iterator.second;

            // - Update the position of the vignette if vignette is linked to a creature or a player
            if (vignette->GeSourceGuid().IsUnit())
            {
                Creature* sourceCreature = ObjectAccessor::GetCreature(*m_Owner, vignette->GeSourceGuid());
                if (sourceCreature != nullptr)
                    vignette->UpdatePosition(G3D::Vector3(sourceCreature->GetPositionX(), sourceCreature->GetPositionY(), sourceCreature->GetPositionZ()));
                Player* sourcePlayer = ObjectAccessor::GetPlayer(*m_Owner, vignette->GeSourceGuid());
                if (sourcePlayer != nullptr)
                    vignette->UpdatePosition(G3D::Vector3(sourcePlayer->GetPositionX(), sourcePlayer->GetPositionY(), sourcePlayer->GetPositionZ()));
            }

            if (vignette->NeedClientUpdate())
            {
                m_UpdatedVignette.insert(vignette->GetGuid());
                vignette->ResetNeedClientUpdate();
            }
        }

        // Send update to client if needed
        if (!m_AddedVignette.empty() || !m_UpdatedVignette.empty() || !m_RemovedVignette.empty())
            SendVignetteUpdateToClient();
    }

    /************************************************************************/
    /*                         HELPERS                                      */
    /************************************************************************/

    /**
    * Return VignetteEntry (db2 entry) from WorldObject if available
    * Work only for Creature, Gameobject and Player
    * @param target : WorldObject for which we wanna get the vignette entry
    */
    inline VignetteEntry const* GetVignetteEntryFromWorldObject(WorldObject const* target) //  Unused function 'GetVignetteEntryFromWorldObject'
    {
        uint32 vignetteId = 0;

        if (target->GetTypeId() == TYPEID_UNIT)
            vignetteId = target->ToCreature()->GetCreatureTemplate()->VignetteID;
        if (target->GetTypeId() == TYPEID_GAMEOBJECT)
            vignetteId = target->ToGameObject()->GetGOInfo()->GetVignetteId();
        if (target->GetTypeId() == TYPEID_PLAYER)
            vignetteId = target->ToPlayer()->GetVignetteID();

        if (vignetteId == 0)
            return nullptr;

        return sVignetteStore.LookupEntry(vignetteId);
    }

    /**
    * Return TrackingQuest (db entry) from WorldObject if available
    * Work only for Creature and Gameobject
    * @param target : WorldObject for which we wanna get the tracking quest
    */
    inline uint32 GetTrackingQuestIdFromWorldObject(WorldObject const* target) //  Unused function 'GetTrackingQuestIdFromWorldObject'
    {
        uint32 trackingQuest = 0;

        if (target->GetTypeId() == TYPEID_UNIT)
            trackingQuest = target->ToCreature()->GetCreatureTemplate()->TrackingQuestID;
        if (target->GetTypeId() == TYPEID_GAMEOBJECT)
            trackingQuest = target->ToGameObject()->GetGOInfo()->GetTrackingQuestId();

        return trackingQuest;
    }

    /**
    * Return default vignette type (@see enum Vignette::Type) from WorldObject
    * Work only for Creature and Gameobject
    * @param target : WorldObject for which we wanna get the default vignette type
    */
    inline Type GetDefaultVignetteTypeFromWorldObject(WorldObject const* target) //  Unused function 'GetDefaultVignetteTypeFromWorldObject'
    {
        switch (target->GetTypeId())
        {
        case TYPEID_UNIT:
            return Type::SourceCreature;
        case TYPEID_GAMEOBJECT:
            return Type::SourceGameObject;
            // Can't happen
        default:
            return Type::SourceScript;
        }
    }

    /**
    * Return tracking vignette type (@see enum Vignette::Type) from WorldObject
    * Work only for Creature and Gameobject
    * @param target : WorldObject for which we wanna get the tracking vignette type
    */
    inline Type GetTrackingVignetteTypeFromWorldObject(WorldObject const* target) // Unused function  GetTrackingVignetteTypeFromWorldObject
    {
        switch (target->GetTypeId())
        {
        case TYPEID_UNIT:
            return Type::SourceRare;
        case TYPEID_GAMEOBJECT:
            return Type::SourceTreasure;
            // Can't happen
        default:
            return Type::SourceScript;
        }
    }
    
    template <class T>
    inline void Manager::OnWorldObjectAppear(T const* target)
    {
        VignetteEntry const* vignetteEntry = GetVignetteEntryFromWorldObject(target);
        if (vignetteEntry == nullptr)
            return;
        
        auto type = GetDefaultVignetteTypeFromWorldObject(target);
        auto trackingQuest = GetTrackingQuestIdFromWorldObject(target);
        
        if (trackingQuest)
        {
            if (m_Owner->IsQuestBitFlaged(sDB2Manager.GetQuestUniqueBitFlag(trackingQuest)))
                return;
            
            type = GetTrackingVignetteTypeFromWorldObject(target);
        }

        if (CanSeeVignette(target, vignetteEntry->Id))
        {
            CreateAndAddVignette(vignetteEntry, target->GetMapId(), type, G3D::Vector3(target->GetPositionX(), target->GetPositionY(), target->GetPositionZ()), target->GetZoneId(), target->GetGUID());

            auto guid = target->GetGUID();
            if (guid.IsPlayer())
                if (auto player = ObjectAccessor::GetPlayer(*m_Owner, guid))
                    player->AddVignetteSee(m_Owner->GetGUID());
        }            
    }
    
    template <class T>
    inline void Manager::OnWorldObjectDisappear(T const* target, bool force /*= false*/)
    {
        auto vignetteEntry = GetVignetteEntryFromWorldObject(target);
        if (vignetteEntry == nullptr)
            return;

        auto guid = target->GetGUID();
        DestroyAndRemoveVignettes([guid, force, this](Vignette::Entity const* vignette) -> bool
        {
            if (vignette->GeSourceGuid() == guid
                && (vignette->GetVignetteType() != Vignette::Type::SourceScript || force))
            {
                if (guid.IsPlayer())
                    if (auto player = ObjectAccessor::GetPlayer(*m_Owner, guid))
                        player->RemoveVignetteSee(m_Owner->GetGUID());
                return true;
            }                
            
            return false;
        });
    }
    
    template <class T>
    bool Manager::CanSeeVignette(T const* obj, uint32 vignetteID)
    {
        if (!vignetteID || (obj->IsUnit() && (!obj->ToUnit()->IsAlive() || (obj->ToUnit()->IsPet() && obj->ToUnit()->GetOwner() && obj->ToUnit()->GetOwner()->IsPlayer()))))
            return false;

        VignetteEntry const* vignette = sVignetteStore.LookupEntry(vignetteID);
        auto cond = sPlayerConditionStore.LookupEntry(vignette->PlayerConditionID);
        if (!vignette)
            return false;

        if (cond && !sConditionMgr->IsPlayerMeetingCondition(const_cast<Player*>(m_Owner), cond))
            return false;

        auto guid = obj->GetGUID();
        uint32 trackingQuest = 0;

        if (guid.IsUnit())
            if (auto creatureSource = ObjectAccessor::GetCreature(*m_Owner, guid))
            {
                trackingQuest = creatureSource->GetTrackingQuestID();
                if (trackingQuest && m_Owner->IsQuestRewarded(trackingQuest))
                    return false;

                if (creatureSource->isDead())
                    return false;
            }

        if (guid.IsGameObject())
            if (auto goSource = ObjectAccessor::GetGameObject(*m_Owner, guid))
            {
                trackingQuest = goSource->GetGOInfo()->GetTrackingQuestId();
                if (trackingQuest && m_Owner->IsQuestRewarded(trackingQuest))
                    return false;
            }

        return true;
    }

    template void Manager::OnWorldObjectDisappear(Corpse const*, bool);
    template void Manager::OnWorldObjectDisappear(Creature const*, bool);
    template void Manager::OnWorldObjectDisappear(GameObject const*, bool);
    template void Manager::OnWorldObjectDisappear(DynamicObject const*, bool);
    template void Manager::OnWorldObjectDisappear(AreaTrigger const*, bool);
    template void Manager::OnWorldObjectDisappear(Conversation const*, bool);
    template void Manager::OnWorldObjectDisappear(WorldObject const*, bool);
    template void Manager::OnWorldObjectDisappear(Player const*, bool);
    template void Manager::OnWorldObjectDisappear(SceneObject const*, bool);

    template void Manager::OnWorldObjectAppear(Corpse const*);
    template void Manager::OnWorldObjectAppear(Creature const*);
    template void Manager::OnWorldObjectAppear(GameObject const*);
    template void Manager::OnWorldObjectAppear(DynamicObject const*);
    template void Manager::OnWorldObjectAppear(AreaTrigger const*);
    template void Manager::OnWorldObjectAppear(Conversation const*);
    template void Manager::OnWorldObjectAppear(WorldObject const*);
    template void Manager::OnWorldObjectAppear(Player const*);
    template void Manager::OnWorldObjectAppear(SceneObject const*);
}
