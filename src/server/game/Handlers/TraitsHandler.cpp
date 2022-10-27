#include "Player.h"
#include "Chat.h"
#include "WorldSession.h"
#include "TalentPackets.h"
#include "DB2Stores.h"
#include "MovementPackets.h"
#include "TraitsMgr.h"
#include "Spell.h"

void WorldSession::HandleLearnTraitsOpcode(WorldPackets::Talent::LearnTraits& learnTraits)
{
    auto traitMgr = _player->GetTraitsMgr();
    if (!traitMgr->GetActiveSpecialization())
        return;

    auto trait = traitMgr->GetTraitByConfigID(learnTraits.Trait.ConfigID);
    if (!trait)
    {
        TC_LOG_ERROR("network.opcode", "Client tried to edit invalid config id");
        // send error
        return;
    }

    auto talentMap = trait->GetTalents();

    for (auto const& talent : learnTraits.Trait.Talents)
    {
        // TODO: Verify talent is for class.

        // learn case - can happen in reset talents respec
        //if (talent.Rank > 0)
        //{
        //    auto it = talentMap->find(talent.TraitNode);
        //    if (it != talentMap->end() && it->second->Rank == talent.Rank)
        //    {
        //        TC_LOG_ERROR("network.opcode", "Client tried to learn already learned talent");
        //        // send error
        //        return;
        //    }
        //}
        //else
        //{
        //    bool hasTalent = talentMap->find(talent.TraitNode) != talentMap->end();
        //    if (!hasTalent)
        //    {
        //        TC_LOG_ERROR("network.opcode", "Client tried to unlearn not learned talent");
        //        // send error
        //        return;
        //    }
        //}
    }

    // SMSG_SUSPEND_TOKEN
    WorldPackets::Movement::SuspendToken tokenPacket;
    tokenPacket.SequenceIndex = _player->m_movementCounter;
    tokenPacket.Reason = 0;
    SendPacket(tokenPacket.Write());

    // SMSG_LEARNED_SPELLS
    if (learnTraits.Loadout == 0 || talentMap->empty())
        _player->GetTraitsMgr()->LearnTraits(learnTraits);
    else
    {
        uint32 loadoutId = learnTraits.Loadout;
        std::vector<WorldPackets::Talent::TraitConfigEntry> traits(learnTraits.Trait.Talents);

        _player->CastAndGetSpell(_player, 384255)->Callback = [this, loadoutId, traits]()
        {
            // packet is actually sending what we are unlearning, so we dont have to unlearn everything here
            _player->GetTraitsMgr()->SwapLoadout(loadoutId, traits);
        };
    }

    // SMSG_RESUME_TOKEN
    WorldPackets::Movement::ResumeToken resumeToken;
    resumeToken.SequenceIndex = _player->m_movementCounter;
    resumeToken.Reason = 0;
    SendPacket(resumeToken.Write());

    // SMSG_UPDATE_OBJECT is sent (handled by map update)
}

void WorldSession::HandleCreateNewLoadoutOpcode(WorldPackets::Talent::CreateNewLoadout& createNewLoadout)
{
    // TODO: research this more
    _player->GetTraitsMgr()->CreateNewLoadout(createNewLoadout);
}

void WorldSession::HandleSwapLoadoutOpcode(WorldPackets::Talent::SwapLoadout& swapLoadout)
{
    _player->GetTraitsMgr()->SwapLoadout(swapLoadout.Loadout);
}

void WorldSession::HandleRenameLoadout(WorldPackets::Talent::RenameLoadout& renameLoadout)
{
    _player->GetTraitsMgr()->RenameLoadout(renameLoadout.ConfigID, renameLoadout.ConfigName);
}

void WorldSession::HandleRemoveLoadout(WorldPackets::Talent::RemoveLoadout& removeLoadout)
{
    _player->GetTraitsMgr()->RemoveLoadout(removeLoadout.ConfigID);
}

void WorldSession::HandleActivateStarterBuild(WorldPackets::Talent::ActiveStarterBuild& setStarterBuild)
{

}
