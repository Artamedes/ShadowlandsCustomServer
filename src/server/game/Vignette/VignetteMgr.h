////////////////////////////////////////////////////////////////////////////////
//
//  NazmirStudio 2018-2020
//
////////////////////////////////////////////////////////////////////////////////

#ifndef VIGNETTE_MGR_HPP
# define VIGNETTE_MGR_HPP
  
# include "Common.h"
# include "Vignette.h"

class WorldObject;
class GameObject;
class Creature;
class Player;

namespace Vignette
{
    using VignetteContainer = std::map<ObjectGuid, Entity*>;

    class Manager
    {
        public:

            /**
            * Constructor of the vignette manager
            * @param player : Owner of the manager
            */
            Manager(Player const* player);

            /**
            * Destructor of the vignette manager
            */
            ~Manager();

            /**
            * Create the vignette and add it to the manager
            * @param vignetteEntry : the db2 entry of the vignette to create
            * @param mapId : The map id where the vignette is
            * @param vignetteType : Type of the vignette, @see Vignette::Type
            * @param position : Position of the vignette
            * @param sourceGuid : Source of the vignette if any (can be gameobject or creature), the vignette will follow the position of the source
            */
            Vignette::Entity* CreateAndAddVignette(VignetteEntry const* vignetteEntry, uint32 const mapId, Vignette::Type const vignetteType, G3D::Vector3 const position, uint32 zoneID, ObjectGuid const sourceGuid = ObjectGuid::Empty);

            /*
            * Remove the vignettes of the manager if they are of the same ID as specified, and destroy them
            * @param vignetteEntry: DB2 entry of the vignette to remove and destroy
            */
            void DestroyAndRemoveVignetteByEntry(VignetteEntry const* vignetteEntry);

            /**
            * Remove the vignettes of the manager and destroy them
            * @param lamba: Function to call for check if the vignette can be remove & destroy
            */
            void DestroyAndRemoveVignettes(std::function < bool(Vignette::Entity* const)> lamba);

            /**
            * Update the vignette manager, send vignette update to client if needed
            */
            void Update();

            /**
            * Call by Player::UpdateVisibilityOf
            * Hook to handle vignettes linked to WorldObjects
            * @param target: The worldobject who appear
            */
            template<class T>
            void OnWorldObjectAppear(T const* target); // Inline function 'Vignette::Manager::OnWorldObjectAppear<WorldObject>' is not defined

            /**
            * Call by Player::UpdateVisibilityOf
            * Hook to handle vignettes linked to WorldObjects
            * @param target: The worldobject who disappear
            * @param force:  Force the disappear by script only
            */
            template<class T>
            void OnWorldObjectDisappear(T const* target, bool force = false); // Inline function 'Vignette::Manager::OnWorldObjectDisappear<WorldObject>' is not defined

            /**
            * Check the vignette if can be see it
            */
            template<class T>
            bool CanSeeVignette(T const* obj, uint32 vignetteID);

        private:

            /**
            * Send to the client creation, update & remove of vignette
            */
            void SendVignetteUpdateToClient();

            Player const*                    m_Owner;                  // Player for who we handle the vignettes
            VignetteContainer                m_Vignettes;              // Contains all the vignette the player can see
            std::set<ObjectGuid>             m_RemovedVignette;        // Contains all the removed vignettes to send to client at the next SMSG_VIGNETTE_UPDATE
            std::set<ObjectGuid>             m_AddedVignette;          // Contains all the added vignettes to send to client at the next SMSG_VIGNETTE_UPDATE
            std::set<ObjectGuid>             m_UpdatedVignette;        // Contains all the updated vignettes to send to client at the next SMSG_VIGNETTE_UPDATE
    };
}

#endif // VIGNETTE_MGR_HPP
