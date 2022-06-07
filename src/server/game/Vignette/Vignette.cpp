////////////////////////////////////////////////////////////////////////////////
//
//  NazmirStudio 2018-2020
//
////////////////////////////////////////////////////////////////////////////////

#include "Vignette.h"
#include "ObjectMgr.h"

namespace Vignette
{
    Entity::Entity(VignetteEntry const* vignetteEntry, uint32 const mapId)
        : m_Map(mapId), m_VignetteEntry(vignetteEntry)
    {

        ASSERT(vignetteEntry != nullptr);

        m_Guid             = ObjectGuid::Empty;
        m_NeedClientUpdate = false;
    }

    Entity::~Entity()
    {
    }

    void Entity::Create(Type type, G3D::Vector3 position, VignetteEntry const* vignetteEntry, uint32 const mapId, uint32 zoneID, ObjectGuid sourceGuid)
    {
        ObjectGuid::LowType guid = sObjectMgr->GenerateNewVignetteGUID();        
        m_Guid = ObjectGuid::Create<HighGuid::Vignette>(mapId, vignetteEntry->Id, guid);
        m_Type       = type;
        m_Position   = position;
        m_SourceGuid = sourceGuid;
        m_zoneID     = zoneID;
    }

    void Entity::UpdatePosition(G3D::Vector3 newPosition)
    {
        if ((int32)m_Position.x == (int32)newPosition.x &&
            (int32)m_Position.y == (int32)newPosition.y)
            return;

        m_Position         = newPosition;
        m_NeedClientUpdate = true;
    }

    void Entity::ResetNeedClientUpdate()
    {
        m_NeedClientUpdate = false;
    }

    ObjectGuid Entity::GetGuid() const
    {
        return m_Guid;
    }

    ObjectGuid Entity::GeSourceGuid() const
    {
        return m_SourceGuid;
    }

    Type Entity::GetVignetteType() const
    {
        return m_Type;
    }

    bool Entity::NeedClientUpdate() const
    {
        return m_NeedClientUpdate;
    }

    G3D::Vector3 const& Entity::GetPosition() const
    {
        return m_Position;
    }

    uint32 Entity::GetZoneID() const
    {
        return m_zoneID;
    }

    VignetteEntry const* Entity::GetVignetteEntry() const
    {
        return m_VignetteEntry;
    }
}
