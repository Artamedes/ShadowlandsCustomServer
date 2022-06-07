////////////////////////////////////////////////////////////////////////////////
//
//  NazmirStudio 2018-2020
//
////////////////////////////////////////////////////////////////////////////////

#ifndef VIGNETTE_H
#define VIGNETTE_H

#include "Common.h"
#include "Creature.h"
#include "Object.h"
#include "DB2Stores.h"
#include "GameObject.h"
#include "ObjectGuid.h"
#include "ObjectMgr.h"
#include "Player.h"
#include <G3D/Vector3.h>

namespace Vignette
{
    // This enum is internal only (not sended or related to client-side)
    // It's represent type of vignette to know how we must handle them
    enum class Type : uint8
    {
        SourceCreature,           // Used for vignette linked to creature, player show the vignette if the creature is in the view-range
        SourceGameObject,         // Used for vignette linked to gameobject, player show the vignette if the gameobject is in the view-range
        SourceRare,               // Used for vignette linked to rare creature, player show the vignette if the creature is in the view-range and if the player doesn't have the tracking quest
        SourceTreasure,           // Used for vignette linked to treasure gameobject, player show the vignette if the treasure is in the view-range and if the player doesn't have the tracking quest
        SourcePlayer,             // Used for vignette linked to player, player show the vignette if the treasure is in the view-range and if the player doesn't have the tracking quest
        SourceScript              // Used for script, that kind of vignette are never remove automaticaly
    };    

    // Entity is the class which represent the vignette
    class Entity
    {
        friend class Manager;

        public:

            /**
            * Update the position of the vignette
            * @param p_NewPosition : New position of the vignette
            */
            void UpdatePosition(G3D::Vector3 newPosition);

            /**
            * Reset the need of client update
            */
            void ResetNeedClientUpdate();

            /**
            * Get the guid of the vignette
            * @return guid : New position of the vignette
            */
            ObjectGuid GetGuid() const;

            /**
            * Get the source guid of the vignette, can be 0
            * @return source guid
            */
            ObjectGuid GeSourceGuid() const;

            /**
            * Get the vignette type
            * @return Type @see Vignette::Type
            */
            Type  GetVignetteType() const;

            /**
            * Check if the vignette need to be update client-side
            * @return result as bool
            */
            bool NeedClientUpdate() const;

            /**
            * Get the current position of the vignette
            * @return Vector3
            */
            G3D::Vector3 const& GetPosition() const;

            /**
            * Get the Vignette Entry (Vignette.db2)
            * @return VignetteEntry
            */
            VignetteEntry const* GetVignetteEntry() const;

            /**
            * Get the current ZoneID
            * @return ZoneID
            */
            uint32 GetZoneID() const;

        private:


            /**
            * Vignette Entity constructor
            * @param vignetteEntry : VignetteEntry, refer to Vignette.db2
            * @param p_MapID : ID of the map where the vignette are, refer to Map.db2
            */
            Entity(VignetteEntry const* vignetteEntry, uint32 const mapId);

            /*
            * Vignette Entity destructor
            */
            ~Entity();

            /**
            * Create the vignette
            * @param type : Type of the vignette, @see enum Vignette::Type
            * @param position: World position of the vignette
            * @param mapId: Current Map ID
            * @param zoneID: Cureny Zone ID
            * @param sourceGuid: Guid of the source (can be gameobject or creature)
            */
            void Create(Type type, G3D::Vector3 position, VignetteEntry const* vignetteEntry, uint32 const mapId, uint32 zoneID, ObjectGuid sourceGuid);

            ObjectGuid           m_Guid;                    // Guid of the current vignette (GUID_TYPE_VIGNETTE)
            ObjectGuid           m_SourceGuid;              // Guid of the source if any (can be gameobject or creature)
            uint32 const         m_Map;                     // Map Id of the current vignette (we only send vignette which are on the same map the player is)
            VignetteEntry const* m_VignetteEntry;           // Vignette data (db2)
            G3D::Vector3         m_Position;                // World coordinates of the current vignette, client compute 2D minimap coord itself
            Type                 m_Type;                    // Type of the vignette, @see enum Vignette::Type
            uint32               m_zoneID;                  // ZoneId for current zone

        protected:

            bool                m_NeedClientUpdate;         // If true, the vignette need to be updated client-side
    };
}
#endif
