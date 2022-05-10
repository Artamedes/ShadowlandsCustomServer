#pragma once

#include "Define.h"

class Player;
class Quest;
class Object;
class ObjectGuid;
struct QuestObjective;

enum QuestObjectiveType : uint8;

class TC_GAME_API QuestAI
{
    uint32 _scriptId;

protected:
    Quest const* quest;
    Player* player;
public:
    explicit QuestAI(Quest const* a, Player* player, uint32 scriptId = {});
    virtual ~QuestAI();

    virtual void OnInitialize() { }

    virtual void Update(uint32 /*diff*/) { }

    virtual void OnQuestAccept() { }
    virtual void OnQuestProgressUpdate(QuestObjectiveType /*objectiveType*/, int32 /*objectId*/, int64 /*addCount*/ , ObjectGuid /*victimGuid*/, uint16 /*logSlot*/, QuestObjective const& /*questObjective*/) { }
    virtual void OnQuestComplete() { }
    virtual void OnQuestIncomplete() { }
    virtual void OnQuestAbandon() { }
    virtual void OnQuestReward(Object* questGiver) { }

    // Gets the id of the AI (script id)
    uint32 GetId() { return _scriptId; }
    bool toRemove = false;
};

class NullQuestAI : public QuestAI
{
    public:
        using QuestAI::QuestAI;
};
