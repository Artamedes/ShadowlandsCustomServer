#include "Player.h"
#include "QuestAI.h"
#include "QuestDef.h"

QuestAI::QuestAI(Quest const* q, Player* p, uint32 scriptId) : _scriptId(scriptId ? scriptId : q->GetScriptId()), quest(q), player(p)
{
}

QuestAI::~QuestAI()
{
}
