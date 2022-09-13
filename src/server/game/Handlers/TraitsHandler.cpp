#include "Player.h"
#include "Chat.h"
#include "WorldSession.h"
#include "TalentPackets.h"
#include "DB2Stores.h"
#include "MovementPackets.h"
#include "TraitsMgr.h"


void WorldSession::HandleLearnTraitsOpcode(WorldPackets::Talent::LearnTraits& learnTraits)
{
    ChatHandler(_player).PSendSysMessage("CMSG_LEARN_TRAITS %u %u", learnTraits.UnkInt32_1, learnTraits.UnkInt32_2);

    ChatHandler(_player).PSendSysMessage("ConfigID: %u Result: %u Talents: %u", learnTraits.Trait.ConfigID, learnTraits.Trait.Result, static_cast<uint32>(learnTraits.Trait.Talents.size()));
    ChatHandler(_player).PSendSysMessage("ConfigName: %s", learnTraits.Trait.ConfigName);

    switch (learnTraits.Trait.Result)
    {
        case 2:
            ChatHandler(_player).PSendSysMessage("Res2Int %u", learnTraits.Trait.Res2Int);
            break;
        case 1:
            ChatHandler(_player).PSendSysMessage("Res1Int_1 %u", learnTraits.Trait.Res1Int_1);
            ChatHandler(_player).PSendSysMessage("Res1Int_2 %u", learnTraits.Trait.Res1Int_2);
            ChatHandler(_player).PSendSysMessage("Res1Int_3 %u", learnTraits.Trait.Res1Int_3);
            break;
        case 3:
            ChatHandler(_player).PSendSysMessage("Res3Int %u", learnTraits.Trait.Res3Int);
            break;
        default:
            ChatHandler(_player).PSendSysMessage("Unk Result was passed %u", learnTraits.Trait.Result);
            break;
    }

    //uint32 i = 0;
    //
    //for (auto const& talent : learnTraits.Trait.Talents)
    //{
    //    auto traitNode = sTraitNodeStore.LookupEntry(talent.TraitNode);
    //    auto traitTree = sTraitTreeStore.LookupEntry(traitNode ? traitNode->TraitTreeID : 0);
    //    auto traitNodeEntry = sTraitNodeEntryStore.LookupEntry(talent.TraitNodeEntryID);
    //    auto traitDefinition = sTraitDefinitionStore.LookupEntry(traitNodeEntry ? traitNodeEntry->TraitDefinitionID : 0);
    //
    //    ChatHandler(_player).PSendSysMessage("[%u] %u %u %u %u %s", i, talent.TraitNode, talent.TraitNodeEntryID, talent.Rank, talent.Unk, traitDefinition ? traitDefinition->OverrideName_lang.Str[0] : "");
    //    if (traitDefinition)
    //        ChatHandler(_player).PSendSysMessage("[%u] TraitDefinition Found! SpellID: %u, OverrideSpellID: %u", i, traitDefinition->SpellID, traitDefinition->OverridesSpellID);
    //    if (traitTree)
    //        ChatHandler(_player).PSendSysMessage("[%u] traitTree Found! %s", i, traitTree->Name);
    //    ++i;
    //}

    // SMSG_SUSPEND_TOKEN
    WorldPackets::Movement::SuspendToken tokenPacket;
    tokenPacket.SequenceIndex = _player->m_movementCounter;
    tokenPacket.Reason = 0;
    SendPacket(tokenPacket.Write());

    // SMSG_LEARNED_SPELLS
    _player->GetTraitsMgr()->LearnTraits(learnTraits);

    // SMSG_RESUME_TOKEN
    WorldPackets::Movement::ResumeToken resumeToken;
    resumeToken.SequenceIndex = _player->m_movementCounter;
    resumeToken.Reason = 0;
    SendPacket(resumeToken.Write());

    // SMSG_UPDATE_OBJECT is sent (handled by map update)

    // swapping (when talents isn't 41?) - hmm seems like Rank being 0 = UNLEARN
    // cast 384255 (Changing Talents)
    // SMSG_SUSPEND_TOKEN
    // SMSG_UNLEARNED_SPELLS
    // SMSG_LEARNED_SPELLS
    // SMSG_RESUME_TOKEN
}

void WorldSession::HandleCreateNewLoadoutOpcode(WorldPackets::Talent::CreateNewLoadout& createNewLoadout)
{
    _player->GetTraitsMgr()->CreateNewLoadout(createNewLoadout);
}
